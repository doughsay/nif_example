#include "erl_nif.h"

// define a struct to act as our resource
typedef struct
{
  int counter;
} CounterResource;

ErlNifResourceType *COUNTER_RES_TYPE;

// the load function tells erlang about any resources we may be returning
int load(ErlNifEnv *env, void **priv_data, ERL_NIF_TERM load_info)
{
  int flags = ERL_NIF_RT_CREATE | ERL_NIF_RT_TAKEOVER;
  COUNTER_RES_TYPE = enif_open_resource_type(env, NULL, "CounterResource", NULL, flags, NULL);

  return 0;
}

// a simple function that returns an atom
static ERL_NIF_TERM
hello_world(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
  return enif_make_atom(env, "hello_world");
}

// a function that returns a counting resource
static ERL_NIF_TERM
new_counter(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
  // wrap the counter in a resource struct
  CounterResource *counter_resource = enif_alloc_resource(COUNTER_RES_TYPE, sizeof(CounterResource));
  counter_resource->counter = 1;

  // convert to erlang resource term and release to erlang memory management
  ERL_NIF_TERM counter_term = enif_make_resource(env, counter_resource);
  enif_release_resource(counter_resource);

  // return {:ok, counter, counter_value}
  return enif_make_tuple3(env, enif_make_atom(env, "ok"), counter_term, enif_make_int(env, counter_resource->counter));
}

// a function that increments the counting resource
static ERL_NIF_TERM
increment_counter(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
  // read arg as counter resource
  CounterResource *counter_resource;
  if (!enif_get_resource(env, argv[0], COUNTER_RES_TYPE, (void **)&counter_resource))
  {
    return enif_make_badarg(env);
  }

  // increment the counter
  counter_resource->counter += 1;

  // return {:ok, counter_value}
  return enif_make_tuple2(env, enif_make_atom(env, "ok"), enif_make_int(env, counter_resource->counter));
}

static ErlNifFunc nif_funcs[] = {
    {"hello_world", 0, hello_world},
    {"new_counter", 0, new_counter},
    {"increment_counter", 1, increment_counter}};

ERL_NIF_INIT(Elixir.NifExample, nif_funcs, &load, NULL, NULL, NULL)
