/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * rdf_init.h - Overall library initialisation / termination prototypes
 *
 * $Id$
 *
 * Copyright (C) 2000-2003 David Beckett - http://purl.org/net/dajobe/
 * Institute for Learning and Research Technology - http://www.ilrt.org/
 * University of Bristol - http://www.bristol.ac.uk/
 * 
 * This package is Free Software or Open Source available under the
 * following licenses (these are alternatives):
 *   1. GNU Lesser General Public License (LGPL)
 *   2. GNU General Public License (GPL)
 *   3. Mozilla Public License (MPL)
 * 
 * See LICENSE.html or LICENSE.txt at the top of this package for the
 * full license terms.
 * 
 * 
 */


#ifndef LIBRDF_INIT_H
#define LIBRDF_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LIBRDF_INTERNAL
struct librdf_world_s
{
  void *error_user_data;
  librdf_log_level_func error_handler;

  void *warning_user_data;
  librdf_log_level_func warning_handler;

  void *log_user_data;
  librdf_log_func log_handler;

  /* static (last) log message */
  librdf_log_message log;

  char *digest_factory_name;
  librdf_digest_factory* digest_factory;

  /* URI interning */
  librdf_hash* uris_hash;
  int uris_hash_allocated_here;

  /* Node interning */
  librdf_hash* nodes_hash[3]; /* resource, literal, blank */

  /* List of parser factories */
  librdf_parser_factory* parsers;

  /* List of serializer factories */
  librdf_serializer_factory* serializers;

  /* List of digest factories */
  librdf_digest_factory *digests;

  /* list of hash factories */
  librdf_hash_factory* hashes;

  /* list of free librdf_hash_datums is kept */
  librdf_hash_datum* hash_datums_list;

   /* hash load_factor out of 1000 */
  int hash_load_factor;

  /* ID base from startup time */
  long genid_base;

  /* Unique counter from there */
  long genid_counter;

#ifdef WITH_THREADS
  /* mutex so we can lock around this when we need to */
  pthread_mutex_t* mutex;

  /* mutex to lock the nodes class */
  pthread_mutex_t* nodes_mutex;
#endif
};

/* internal routines used to invoking errors/warnings upwards to user */
REDLAND_DEPRECATED void librdf_error(librdf_world* world, const char *message, ...);
REDLAND_DEPRECATED void librdf_warning(librdf_world* world, const char *message, ...);

unsigned char* librdf_world_get_genid(librdf_world* world);

#endif

REDLAND_API librdf_world* librdf_new_world(void);
REDLAND_API void librdf_free_world(librdf_world *world);
REDLAND_API void librdf_world_open(librdf_world *world);

REDLAND_API void librdf_world_init_mutex(librdf_world *world);
  
REDLAND_API void librdf_world_set_error(librdf_world* world, void *user_data, librdf_log_level_func error_handler);
REDLAND_API void librdf_world_set_warning(librdf_world* world, void *user_data, librdf_log_level_func warning_handler);
REDLAND_API void librdf_world_set_logger(librdf_world* world, void *user_data, librdf_log_func log_handler);

REDLAND_API void librdf_world_set_digest(librdf_world*, const char *name);
REDLAND_API void librdf_world_set_uris_hash(librdf_world* world, librdf_hash* uris_hash);


#define LIBRDF_WORLD_FEATURE_GENID_BASE "http://feature.librdf.org/genid-base"
#define LIBRDF_WORLD_FEATURE_GENID_COUNTER "http://feature.librdf.org/genid-counter"

REDLAND_API const char *librdf_world_get_feature(librdf_world* world, librdf_uri *feature);
REDLAND_API int librdf_world_set_feature(librdf_world* world, librdf_uri *feature, const char *value);

/* OLD INTERFACES */
REDLAND_API REDLAND_DEPRECATED void librdf_init_world(char *digest_factory_name, void* not_used2);
REDLAND_API REDLAND_DEPRECATED void librdf_destroy_world(void);

#ifdef __cplusplus
}
#endif

#endif
