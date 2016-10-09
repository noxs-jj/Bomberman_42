#/bin/bash
APP_REPO_ABSOLUTE_PATH=$(dirname $(readlink -f $0))

while true; do
  bash -l -c "cd $APP_REPO_ABSOLUTE_PATH && $APP_REPO_ABSOLUTE_PATH/bomberman -arcade"
  sleep 3
done
