#ifndef PG_LOGICAL_COMPAT_H
#define PG_LOGICAL_COMPAT_H

#include "pgstat.h"
#include "catalog/indexing.h"
#include "commands/trigger.h"
#include "executor/executor.h"
#include "replication/origin.h"

#define PGLCreateTrigger CreateTrigger

#define RawStmt Node

#define	PGLDoCopy(stmt, queryString, processed) DoCopy(stmt, queryString, processed)

#ifdef PGXC
#define PGLstandard_ProcessUtility(pstmt, queryString, context, params, queryEnv, dest, sentToRemote, completionTag) \
	standard_ProcessUtility(pstmt, queryString, context, params, dest, sentToRemote, completionTag)

#define PGLnext_ProcessUtility_hook(pstmt, queryString, context, params, queryEnv, dest, sentToRemote, completionTag) \
	next_ProcessUtility_hook(pstmt, queryString, context, params, dest, sentToRemote, completionTag)

#else

#define PGLstandard_ProcessUtility(pstmt, queryString, context, params, queryEnv, dest, sentToRemote, completionTag) \
	standard_ProcessUtility(pstmt, queryString, context, params, dest, completionTag)

#define PGLnext_ProcessUtility_hook(pstmt, queryString, context, params, queryEnv, dest, sentToRemote, completionTag) \
	next_ProcessUtility_hook(pstmt, queryString, context, params, dest, completionTag)
#endif

extern Oid CatalogTupleInsert(Relation heapRel, HeapTuple tup);
extern void CatalogTupleUpdate(Relation heapRel, ItemPointer otid, HeapTuple tup);
extern void CatalogTupleDelete(Relation heapRel, ItemPointer tid);

#define pgl_replorigin_drop(roident) \
	replorigin_drop(roident)

#define pgl_heap_attisnull(tup, attnum, tupledesc) \
	heap_attisnull(tup, attnum)

#ifndef rbtxn_has_catalog_changes
#define rbtxn_has_catalog_changes(txn) (txn->has_catalog_changes)
#endif

#endif
