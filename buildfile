./: tests/ manifest doc{*.md} legal{COPYING}

./: lib{lyrahgames-gnuplot-pipe}: lyrahgames/hxx{**}
{
  cxx.export.poptions = "-I$out_root" "-I$src_root"
}
hxx{**}: install.subdirs = true

tests/: install = false