#include "../include/test_suite.h"
#include <iostream>

int main() {
    std::cout << "=== SISTEMA DE NAVEGACIÓN - SUITE DE PRUEBAS ===" << std::endl;
    std::cout << "Proyecto Final - Algoritmos y Estructura de Datos" << std::endl;
    std::cout << "Validando todas las funcionalidades del sistema..." << std::endl;
    std::cout << std::endl;
    
    TestSuite test_suite;
    test_suite.runAllTests();
    
    // Determinar código de salida basado en los resultados
    if (test_suite.getTestsFailed() == 0) {
        std::cout << "\n🎉 SISTEMA VALIDADO EXITOSAMENTE" << std::endl;
        return 0; // Éxito
    } else {
        std::cout << "\n❌ SISTEMA REQUIERE CORRECCIONES" << std::endl;
        return 1; // Fallo
    }
}

