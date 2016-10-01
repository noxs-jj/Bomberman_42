#/bin/bash
APP_REPO_ABSOLUTE_PATH=$(dirname $(readlink -f $0))

while sleep 2; do $APP_REPO_ABSOLUTE_PATH/bomberman -arcade; done
