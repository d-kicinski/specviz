JNI_SOURCES = $(wildcard jni/*.cpp)
KT_SOURCES = $(wildcard src/**/*.kt)

BUILD_DIR=build
LIB_NAME = libNativeKotlinSample.so
JAR_NAME = native-kotlin-sample.jar

all: show clean prepare build_native build_kotlin run

show:
	@echo JNI sources: ${JNI_SOURCES}
	@echo KT: sources: ${KT_SOURCES}
	@echo JAVA_PATH = ${JAVA_PATH}
	@echo KOTLIN_PATH = ${KOTLIN_PATH}
	@echo C = $C
	@echo CXX = ${CXX}

build_native:
	${CXX} -shared -fPIC -I ${JAVA_PATH}/include -I ${JAVA_PATH}/include/linux ${JNI_SOURCES} -o ${LIB_NAME}

	mv ${LIB_NAME} ${BUILD_DIR}/

build_kotlin:
	${KOTLIN_PATH}/bin/kotlinc -include-runtime -d ${JAR_NAME} src/sam/Main.kt src/sam/NativeSample.kt
	mv ${JAR_NAME} ${BUILD_DIR}/

run:
	LD_LIBRARY_PATH=${BUILD_DIR} java -jar ${BUILD_DIR}/${JAR_NAME}

prepare:
	mkdir -p ${BUILD_DIR}

clean:
	rm -rf ${BUILD_DIR}

.PHONY: clean