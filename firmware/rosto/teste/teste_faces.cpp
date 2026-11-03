// Confere a tabela de rostos no computador, sem placa:
//   c++ -std=c++17 firmware/rosto/teste/teste_faces.cpp -o /tmp/teste_faces && /tmp/teste_faces
// (fica fora da raiz do sketch porque o Arduino compila todo .cpp da raiz junto)
// Com "--ver", imprime todos os quadros em texto para revisar o desenho.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "../rosto_faces.h"

int main(int argc, char **argv) {
  bool ver = argc > 1 && strcmp(argv[1], "--ver") == 0;
  assert(FACE_COUNT == 10);
  for (int f = 0; f < FACE_COUNT; f++) {
    const Face &face = FACES[f];
    assert(face.count >= 1);
    for (int g = 0; g < f; g++) assert(strcmp(face.name, FACES[g].name) != 0);
    for (int q = 0; q < face.count; q++) {
      const Frame &fr = face.frames[q];
      assert(fr.ms > 0);
      if (ver) printf("%s, quadro %d (%d ms)\n", face.name, q, fr.ms);
      for (int y = 0; y < GRID_H; y++) {
        const char *row = fr.rows[y];
        assert(row && "linha faltando");
        if (strlen(row) != GRID_W) {
          fprintf(stderr, "%s quadro %d linha %d: %zu colunas, esperado %d\n",
                  face.name, q, y, strlen(row), GRID_W);
          return 1;
        }
        assert(strspn(row, "#+.") == GRID_W && "caractere fora de '#', '+' e '.'");
        if (ver) printf("  %s\n", row);
      }
    }
  }
  printf("ok: %d rostos conferidos\n", FACE_COUNT);
}
