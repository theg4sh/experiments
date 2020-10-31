#include <hash/fnv/fnv1a.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "usage: " << argv[0] << " <any-string>" << std::endl;
    return 1;
  }
  const std::string hash_this(argv[1]);
  auto hash = ::hash::fnv::fnv1a<unsigned char>(hash_this);

  std::cout << "Orig: " << hash_this << std::endl;
  std::cout << "Hash: " << hash << std::endl;
  return 0;
}
