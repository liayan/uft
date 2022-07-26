/*
 * Copyright (c) 2022 Digital Ocean
 *
 * Licensed under the GNU General Public License Version 3
 * as published by the Free Software Foundation.
 *
 * See http://www.gnu.org/licenses/licenses/gpl-3.0.html
 * for details.
 *
 * Author: Liang Yan <lyan@digitalocean.com>
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <git2.h>

#if LIBGIT2_VER_MAJOR == 0 && LIBGIT2_VER_MINOR < 22
#error "libgit2 version 0.22.0 or newer is required. Try 'make BUILD_LIBGIT2=1'"
#endif

using namespace std;

struct options {
	string repo_path;
	string revision;
	string committer;
	string fixes_file;
	string bl_keyword;
	string bl_file;
	string bl_path_file;
	string db;
        string base;
	bool all_cmdline;
	bool all;
	bool match_all;
	bool no_group;
	bool reverse;
	bool no_blacklist;
	bool parsable;
	bool patch;
	vector<string> path;
	vector<string> bl_path;
};

struct commit {
	string subject;
	string context;
	string id;
	string path;


	vector<struct reference> refs;

	commit() { };
};

struct reference {
	string id;
	bool fixes;
	bool cve;

	reference()
		: id(), fixes(false), cve(false)
	{ }
};

struct match_info {
	string commit_id;
	string committer;
	string path;

	bool operator<(const struct match_info &i) const
	{
		return commit_id < i.commit_id;
	}
};

vector<struct match_info> match_list;
map<string, vector<commit> > results;
map<string, string> reverts;
vector<string> blacklist;
vector<string> bl_keywords;
git_pathspec *bl_pathspec;

enum {
	OPTION_HELP,
	OPTION_ALL,
	OPTION_REPO,
	OPTION_REVERSE,
	OPTION_COMMITTER,
	OPTION_GROUPING,
	OPTION_NO_GROUPING,
	OPTION_MATCH_ALL,
	OPTION_FILE,
	OPTION_BL_KEYWORD,
	OPTION_BLACKLIST,
	OPTION_NO_BLACKLIST,
	OPTION_DATA_BASE,
	OPTION_BASE,
	OPTION_PARSABLE,
	OPTION_BL_FILE,
	OPTION_PATCH
};

static struct option options[] = {
	{ "help",		no_argument,		0, OPTION_HELP           },
	{ "all",		no_argument,		0, OPTION_ALL            },
	{ "repo",		required_argument,	0, OPTION_REPO           },
	{ "reverse",		no_argument,		0, OPTION_REVERSE        },
	{ "committer",		required_argument,	0, OPTION_COMMITTER      },
	{ "grouping",		no_argument,		0, OPTION_GROUPING       },
	{ "no-grouping",	no_argument,		0, OPTION_NO_GROUPING    },
	{ "match-all",		no_argument,		0, OPTION_MATCH_ALL      },
	{ "data-base",		required_argument,	0, OPTION_DATA_BASE      },
	{ "file",		required_argument,	0, OPTION_FILE           },
	{ "bl-keyword",	        required_argument,	0, OPTION_BL_KEYWORD    },
	{ "blacklist",	        required_argument,	0, OPTION_BLACKLIST      },
	{ "no-blacklist",	no_argument,		0, OPTION_NO_BLACKLIST   },
	{ "base",		no_argument,		0, OPTION_BASE          },
	{ "parsable",		no_argument,		0, OPTION_PARSABLE       },
	{ "bl-file",	        required_argument,	0, OPTION_BL_FILE },
	{ "patch",		no_argument,		0, OPTION_PATCH          },
	{ 0,			0,			0, 0                     }
};

static void usage(const char *prg)
{
	printf("Usage: %s [Options] \n", prg);
	printf("Options:\n");
	printf("  --help, -h       Print this message end exit\n");
	printf("  --base, -b       Set the base branch or tag id\n");
	printf("  --repo, -r       Path to git repo (defaults to '.')\n");
	printf("  --all, -a        Show all potential fixes\n");
	printf("  --reverse        Sort fixes in reverse order\n");
	printf("  --committer, -c  Show only fixes for a given committer\n");
	printf("  --grouping       Group fixes by committer (default)\n");
	printf("  --no-grouping    Don't group fixes by committer\n");
	printf("  --match-all, -m  Match against everything that looks like a git commit-id\n");
	printf("  --data-base, -d  Select specific data-base (set file with fixes.<db>.file)\n");
	printf("  --extra, -e      Read commit-list from file\n");
	printf("  --bl-keyword -k  Specify a file with keywords to blacklist the\n");
	printf("                   commit-list we do not care\n");
	printf("                   Use this to filter fixes that contain the keyword\n");
	printf("  --blacklist,     Read blacklist from file\n");
	printf("  --no-blacklist,  Also show blacklisted commits\n");
	printf("  --parsable, -p   Print machine readable output\n");
	printf("  --bl-file        Filename containing the src file names that want to blaclist \n");
	printf("  --patch          Print patch-filename the fix is for (if available)\n");
}