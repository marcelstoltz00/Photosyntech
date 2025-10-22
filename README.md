# PhotoSyntech

![Unit Tests](https://github.com/marcelstoltz00/Photosyntech/actions/workflows/cpp-tests.yml/badge.svg)
![Code Coverage](https://img.shields.io/badge/coverage-dynamic-brightgreen)

PhotoSyntech is a C++ plant management system demonstrating multiple design patterns.

## Features

- Plant management and tracking
- Growth and care simulation
- Multiple design patterns including:
  - Builder
  - Iterator
  - Observer
  - Strategy
  - Decorator
  - State
  - And more!

## Getting Started

### Prerequisites

- C++ compiler supporting C++11
- Make build system

### Building

```bash
make all
```

### Running Tests

```bash
make test-run
```

### Generating Coverage Report

```bash
make cov
```

## Project Structure

- `builder/` - Implementation of the Builder pattern
- `command/` - Implementation of the Command pattern
- `composite/` - Implementation of the Composite pattern
- `decorator/` - Implementation of the Decorator pattern
- `iterator/` - Implementation of the Iterator pattern
- And more!

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[MIT](https://choosealicense.com/licenses/mit/)