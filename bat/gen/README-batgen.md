# Operations Generators

The components in `batgen` are intended to avoid boiler-plate code
needed when creating certain kinds of classes. The general pattern
used is to [privately] inherit from a genertor class to have the
operations provided.

There are components to generate symmetric operators based on
provision of a subset of the operators. There are also components
generating operations based on a type definition listing all members.
The approach is similar to using a `std::tuple`.
