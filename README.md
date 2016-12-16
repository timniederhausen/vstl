# vstl

Compatibility shims for standard library features.

Several standard library features (e.g. polymorphic allocators)
aren't yet implemented in some (all?) widely used standard library implementations.

vstl uses the standard versions (if possible), otherwise falling back on Boost
or custom implementations (if there's no suitable version in Boost).

*Note*: Right now vstl also contains a bunch of utility functions (e.g. for working
with containers), which aren't part of standard/TS.

## Shims

* ``vstd::string`` -> ``std::pmr::string`` (alt: ``boost::container::pmr::string``)
* ``vstd::string_view`` -> ``std::basic_string_view`` (alt: custom)
* ``vstd::vector`` -> ``std::pmr::vector``  (alt: ``boost::container::pmr::vector``)

## License

Please see [LICENSE_1_0.txt](LICENSE_1_0.txt).
