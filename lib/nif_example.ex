defmodule NifExample do
  @on_load :load_nifs

  def load_nifs do
    :erlang.load_nif('./priv/nif_example', 0)
  end

  def hello_world do
    :erlang.nif_error("NIF hello_world/0 not implemented")
  end

  def new_counter do
    :erlang.nif_error("NIF new_counter/0 not implemented")
  end

  def increment_counter(_counter) do
    :erlang.nif_error("NIF increment_counter/1 not implemented")
  end
end
