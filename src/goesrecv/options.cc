#include "options.h"

#include <getopt.h>
#include <stdlib.h>

#include <iostream>

void usage(int argc, char** argv) {
  fprintf(stderr, "Usage: %s [OPTIONS]\n", argv[0]);
  fprintf(stderr, "Demodulate and decode signal into packet stream.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "Options:\n");
  fprintf(stderr, "  -c, --config PATH          Path to configuration file\n");
  fprintf(stderr, "      --help                 Show this help\n");
  fprintf(stderr, "\n");
  exit(0);
}

Options parseOptions(int argc, char** argv) {
  Options opts;

  while (1) {
    static struct option longOpts[] = {
      {"config", required_argument, 0, 'c'},
      {"help", no_argument, 0, 0x1337},
    };

    auto c = getopt_long(argc, argv, "d:", longOpts, nullptr);
    if (c == -1) {
      break;
    }

    switch (c) {
    case 0:
      break;
    case 'c':
      opts.config = optarg;
      break;
    case 0x1337:
      usage(argc, argv);
      break;
    default:
      std::cerr << "Invalid option" << std::endl;
      exit(1);
    }
  }

  if (opts.config.empty()) {
    std::cerr << "Please specify configuration file" << std::endl;
    exit(1);
  }

  return opts;
}
