./: manifest doc{README.md AUTHORS.md} legal{COPYING.md}

./: lyrahgames/

./: tests/
tests/: install = false

./: examples/
examples/: install = false
# Disable tests by default.
# Run 'b test: examples/' instead.
examples/exe{*}: test = false
