#include "erl_nif.h"

// a simple funciton that returns an atom
static ERL_NIF_TERM
hello_world(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
  return enif_make_atom(env, "hello_world");
}

static ErlNifFunc nif_funcs[] = {
    {"hello_world", 0, hello_world}};

ERL_NIF_INIT(Elixir.NifExample, nif_funcs, NULL, NULL, NULL, NULL)
