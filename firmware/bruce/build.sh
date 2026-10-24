#!/usr/bin/env bash
# Compila (e, com "upload", grava) o Bruce para o BMO v1.
# Uso: firmware/bruce/build.sh [pasta-do-clone-do-bruce] [upload]
# Baixa o Bruce na versão fixada se a pasta ainda não existir e copia a placa do BMO para
# boards/bmo dele.
#
# PlatformIO: a plataforma do Bruce exige Python 3.10 a 3.14, e o platformio do Homebrew
# vem com Python mais novo. Instalar num venv próprio:
#   python3.14 -m venv ~/.platformio/penv && ~/.platformio/penv/bin/pip install platformio
set -euo pipefail

BRUCE_VERSAO=1.16.1
AQUI="$(cd "$(dirname "$0")" && pwd)"
CLONE="${1:-$HOME/.cache/bruce-$BRUCE_VERSAO}"
PIO="${PIO:-$HOME/.platformio/penv/bin/pio}"
# Os scripts de build do Bruce chamam "pio" pelo nome (patch da libnet80211).
export PATH="$(dirname "$PIO"):$PATH"

if [ ! -d "$CLONE" ]; then
  git clone --depth 1 --branch "$BRUCE_VERSAO" https://github.com/pr3y/Bruce.git "$CLONE"
fi

mkdir -p "$CLONE/boards/bmo"
cp "$AQUI/bmo.ini" "$AQUI/interface.cpp" "$CLONE/boards/bmo/"

cd "$CLONE"
if [ "${2:-}" = "upload" ]; then
  "$PIO" run -e bmo-v1 -t upload
else
  "$PIO" run -e bmo-v1
fi
