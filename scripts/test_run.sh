
cd build

if [ -z "$1" ]
  then
    echo " no arg"
    ./mainTest
  else
  echo "have arh" $1
    ./mainTest --gtest_filter=RunTest.$1
fi

cd -