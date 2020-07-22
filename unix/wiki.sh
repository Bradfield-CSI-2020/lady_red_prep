#!/usr/local/bin/bash
VERBOSE=""
TITLE=$1
if [[ $TITLE == "" ]]; then 
  TITLE="walrus"
fi
echo $TITLE


# Capitalize
TITLE=`echo "${TITLE^}" | tr " " "_"`

WIKI_API="https://en.wikipedia.org/w/api.php"
GET="action=query&prop=extracts&exsentences=2&format=json&exintro=true&explaintext=true&titles=${TITLE}"


URL="${WIKI_API}?$GET"
if [[ $VERBOSE ]]; then 
  echo $BASH_VERSION
  echo $TITLE
  echo $URL
fi

WIKI=`curl  -s $URL | grep -o \"extract\":\".*\"`

SUMMARY="${WIKI:11:-1}"
# echo `head <(echo $WIKI)`
echo -e "$SUMMARY"
# echo $curl_out

 