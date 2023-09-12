// tareas

#include "tareas.h"
#include <iostream>
#include <map>
#include <opencv2/opencv.hpp>

// Mutex y variable de condición
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// Recurso compartido: biblioteca de filtros
bool isFilterLibraryInUse = false;

// Mapa para almacenar tareas activas
std::map<int, pthread_t> activeTasks;

// Función para aplicar un filtro de ejemplo (blanco y negro)
cv::Mat applyBlackAndWhiteFilter(const cv::Mat& src) {
    cv::Mat dst;
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
    return dst;
}

// Función que ejecutará cada hilo
void* taskFunction(void* arg) {
    TaskData* data = (TaskData*)arg;

    // Leer la imagen desde el sistema de archivos
    cv::Mat image = cv::imread(data->taskName);  // Aquí, taskName es el nombre del archivo de la imagen

    // Solicitar acceso al recurso compartido
    pthread_mutex_lock(&mutex);
    while (isFilterLibraryInUse) {
        pthread_cond_wait(&cond, &mutex);
    }

    // Acceder al recurso compartido
    isFilterLibraryInUse = true;

    // Aplicar el filtro
    cv::Mat processedImage = applyBlackAndWhiteFilter(image);

    // Liberar recurso compartido
    isFilterLibraryInUse = false;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    // Mostrar la imagen procesada en la interfaz (esto es solo un ejemplo, deberás adaptarlo)
    cv::imshow("Processed Image", processedImage);
    cv::waitKey(0);

    delete data;
    return nullptr;
}

void addTask(TaskData* data) {
    pthread_t thread;
    pthread_create(&thread, nullptr, taskFunction, data);
    activeTasks[data->taskId] = thread;
}

void removeTask(int taskId) {
    if (activeTasks.find(taskId) != activeTasks.end()) {
        pthread_cancel(activeTasks[taskId]);
        activeTasks.erase(taskId);
    }
}
