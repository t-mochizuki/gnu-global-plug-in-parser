if [[ ! -d global-6.5.6 ]]; then
  curl -O http://tamacom.com/global/global-6.5.6.tar.gz
  tar zxf global-6.5.6.tar.gz
fi

cp plugin-factory/user-custom.c global-6.5.6/plugin-factory/user-custom.c
cd global-6.5.6

if [[ ! -f Makefile ]]; then
  ./configure --prefix=/usr/local/global
fi

make -j 4
