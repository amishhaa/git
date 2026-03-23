#include "git-compat-util.h"
#include "builtin.h"
#include "repository.h"
#include "object-name.h"
#include "parse-options.h"
#include "run-command.h"
#include "hex.h"
#include "strbuf.h"

int cmd_evict(int argc, const char **argv, const char *prefix, struct repository *repo)
{
    struct object_id oid;
    
    if (argc < 2) {
        fprintf(stderr, "usage: git evict <object>\n");
        return 1;
    }

    if (repo_get_oid(repo, argv[1], &oid)) {
        error("bad object: %s", argv[1]);
        return 1;
    }
    setenv("GIT_EVICT_OID", oid_to_hex(&oid), 1);
    const char *repack_argv[] = { "repack", "-a", "-d", NULL };
    return cmd_repack(3, repack_argv, prefix, repo);
}