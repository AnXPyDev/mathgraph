#!bash

SOURCE_DIR=src;
BUILD_DIR=build;
DIFF_DIR=diff;
INCLUDE_DIR=include;
OBJECT_EXTENTION=cpp;
NAME=mathgraph;

CC=g++;
CC_ARGS=;
CC_OBJECT_ARGS="-c -I $INCLUDE_DIR";
CC_MAIN_ARGS=;

success_message="+success"
fail_message="-fail"

function find_directories {
  directories="\n$(find $SOURCE_DIR -type d -mindepth 1 | sed -e "s/$SOURCE_DIR\///g")";
}

function find_objects {
  objects="$(find $SOURCE_DIR -type f -regex ".*\.$OBJECT_EXTENTION" | sed -e "s/$SOURCE_DIR\///g" -e "s/\.$OBJECT_EXTENTION//g")";
}

function create_diff_dir {
  if [[ -d $DIFF_DIR ]]; then
    echo -e "updating diff directory: \"$DIFF_DIR\" \c";
    cp -rf $SOURCE_DIR/* $DIFF_DIR/ && echo -e $success_message || echo -e $fail-message;
  else
    echo -e "creating diff directory: \"$DIFF_DIR\" \c";
    cp -rf $SOURCE_DIR $DIFF_DIR && echo -e $success_message || echo -e $fail-message;
  fi
}

function create_build_dir {
  echo -e "$directories" | while read directory; do
    echo -e "creating build directory: \"$BUILD_DIR/$directory\" \c";
    mkdir -p $BUILD_DIR/$directory && echo -e $success_message || echo -e $fail_message;
  done;
}

function clean {
  echo -e "removing build directory: \"$BUILD_DIR\" \c" && rm -rf $BUILD_DIR && echo -e $success_message || echo -e $fail_message;
  echo -e "removing diff directory: \"$DIFF_DIR\" \c" && rm -rf $DIFF_DIR && echo -e $success_message || echo -e $fail_message;
}

function _build_objects {
  echo -e "$objects" | while read object; do
    if [[ ( ! -f "$BUILD_DIR/$object.o" ) || ( ( -f "$DIFF_DIR/$object.$OBJECT_EXTENTION" ) && $(diff -q "$DIFF_DIR/$object.$OBJECT_EXTENTION" "$SOURCE_DIR/$object.$OBJECT_EXTENTION") ) ]]; then
      echo -e "building object: \"$object\" \c";
      if $CC $CC_ARGS $CC_OBJECT_ARGS "$SOURCE_DIR/$object.$OBJECT_EXTENTION" -o "$BUILD_DIR/$object.o"; then
        echo -e $success_message;
      else
        echo -e $fail_message;
      fi
    else
      echo -e "skipping object: \"$object\"";
    fi
  done
}

function create_executable {
  built_object_paths=$(echo -e "$objects" | while read object; do echo -e "$BUILD_DIR/$object.o \c"; done)
  echo -e "linking objects into executable: \"$NAME\" \c";
  $CC $CC_ARGS $CC_MAIN_ARGS $built_object_paths -o $NAME && echo -e $success_message || echo -e $fail_message;
}

function build_objects {
  create_build_dir;
  _build_objects;
  create_diff_dir;
}

function main {
  build_objects;
  create_executable;
}

find_directories;
find_objects;

echo $@ | sed -e "s/\ /\n/g" | while read arg; do
  $arg;
done

if [[ -z "$@" ]]; then
  main;
fi
