defmodule NifExample do
  @on_load :load_nifs

  def load_nifs do
    :erlang.load_nif('./priv/nif_example', 0)
  end

  def hello_world do
    :erlang.nif_error("NIF hello_world/0 not implemented")
  end
end
