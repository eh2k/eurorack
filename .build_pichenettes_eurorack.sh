
cd mutable-dev-env && docker build . -t mi-dev-en && cd -

git submodule update --init --recursive

docker run -v $(pwd)/build:/home/eurorack/build -v $(pwd)/pichenettes_eurorack:/home/eurorack mi-dev-env make -f grids/bootloader/makefile
docker run -v $(pwd)/build:/home/eurorack/build -v $(pwd)/pichenettes_eurorack:/home/eurorack mi-dev-env make -f grids/makefile

docker run -v $(pwd)/build:/home/eurorack/build \
           -v $(pwd)/braids_tht/encoder.h:/home/eurorack/braids/drivers/encoder.h \
           -v $(pwd)/braids_tht/encoder.cc:/home/eurorack/braids/drivers/encoder.cc \
           -v $(pwd)/braids_tht/dac.h:/home/eurorack/braids/drivers/dac.h \
           -v $(pwd)/pichenettes_eurorack:/home/eurorack \
           mi-dev-env make -f braids/bootloader/makefile

docker run -v $(pwd)/build:/home/eurorack/build \
           -v $(pwd)/braids_tht/encoder.h:/home/eurorack/braids/drivers/encoder.h \
           -v $(pwd)/braids_tht/encoder.cc:/home/eurorack/braids/drivers/encoder.cc \
           -v $(pwd)/braids_tht/dac.h:/home/eurorack/braids/drivers/dac.h \
           -v $(pwd)/pichenettes_eurorack:/home/eurorack \
           mi-dev-env make -f braids/makefile wav