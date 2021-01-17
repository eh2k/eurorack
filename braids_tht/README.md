### build mi-dev-env docker image

````
docker build . -t mi-dev-env
````

### make & flash firmware

````
docker run -v $(pwd):/home/eurorack/build mi-dev-env make -f braids/makefile
stm32flash -g 0x8000000 -b 115200 -w ./braids/braids.hex /dev/ttyUSB0
````

### make & flash bootloader

````
docker run -v $(pwd):/home/eurorack/build mi-dev-env make -f braids/bootloader/makefile
stm32flash -g 0x0 -b 115200 -w ./braids_bootloader/braids_bootloader.hex /dev/ttyUSB0
````



