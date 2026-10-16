# Changelog

All notable changes to this project will be documented in this file.

## [1.0.1]

### Added
- Error logging when Lilu callback registration or route installation fails.

### Changed
- Migrated kernel hook routing from deprecated `routeFunctionLong` to `routeMultipleLong` (`RouteRequest`) for safe chained hook execution.
- Hardened page validation hook with null-pointer checks.
- Updated Lilu dependency requirement to 1.7.2.



