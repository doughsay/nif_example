defmodule NifExampleTest do
  use ExUnit.Case
  doctest NifExample

  test "greets the world" do
    assert NifExample.hello() == :world
  end
end
