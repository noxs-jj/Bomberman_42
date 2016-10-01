#/bin/bash
APP_REPO_ABSOLUTE_PATH=$(dirname $(readlink -f $0))

while true; do
  bash -l -c "$APP_REPO_ABSOLUTE_PATH/bomberman -arcade -noparticle"
  sleep 2
done
