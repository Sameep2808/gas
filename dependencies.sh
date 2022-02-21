### For opencv
git clone https://github.com/opencv/opencv.git
cd opencv 
git checkout 4.5.0
cd ..
git clone https://github.com/opencv/opencv_contrib.git
cd opencv_contrib
git checkout 4.5.0
cd ..
cd opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D BUILD_EXAMPLES=OFF \
      -D BUILD_opencv_apps=OFF \
      -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
      -D BUILD_DOCS=OFF \
      -D BUILD_PERF_TESTS=OFF \
      -D BUILD_TESTS=OFF \
      -D WITH_CUDA=OFF \
      -D CMAKE_INSTALL_PREFIX=/usr/local ..
      
make 
sudo make install
sudo sh -c 'echo "/usr/local/lib" >> /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig
