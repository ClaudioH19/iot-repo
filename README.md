# Taller introductorio: Git, GitHub y Wokwi

**Ejercicio individual:** completar las conexiones de un Arduino UNO, un DHT22, dos LED y dos resistencias. **El codigo sketch.ino ya esta completo y comentado.** No hay cables en el diagrama del alumno.

## Archivos
- `sketch.ino`: ejecuta automaticamente un dia ficticio y controla las dos alertas; tambien permite leer un DHT22.
- `diagram.json`: contiene todos los componentes SIN conectar: tu tarea es cablearlos.
- `libraries.txt`: dependencias de la biblioteca DHT22.
- `REFERENCIA.md`: instrucciones basicas de C++ y Arduino con ejemplos.

## 1. Comprobar el dia automatico (modo inicial)
1. Abre los archivos en Wokwi con Arduino UNO. Inicia la simulacion **sin cables**.
2. Abre el monitor serie. Debe aparecer `MODO: dia ficticio automatico (sin lectura DHT22)`.
3. Cada **3 segundos**, el programa muestra un nuevo momento del dia: 00:00, 03:00, 06:00, 09:00, 12:00, 15:00, 18:00 y 21:00, luego vuelve a 00:00.
4. Temperatura sube durante el dia y humedad baja, y a la inversa hacia la noche. **Son datos de ejemplo**, no mediciones del sensor.
5. Inicialmente no veras encender LED, porque estan sin cablear. Pero los valores y las alertas ya se calculan en el codigo.

## 2. Cablear el circuito
Deten la simulacion. Haz estas conexiones:

### DHT22
- **Arduino 5V -> VCC del DHT22**.
- **Arduino GND -> GND del DHT22**.
- **Arduino D2 -> SDA del DHT22**.
- No conectar `NC`.

### LED rojo y azul
- **Arduino D8 -> resistencia de 220 ohm -> A (anodo) del LED rojo**; **C (catodo) -> GND**.
- **Arduino D9 -> resistencia de 220 ohm -> A (anodo) del LED azul**; **C (catodo) -> GND**.
- Cada resistencia debe estar en serie con su LED.

## 3. Probar el dia ficticio con LEDs conectados
1. Inicia Wokwi de nuevo, deja `const bool DIA_AUTOMATICO = true;`.
2. Observa: a las 03:00 y 06:00 el LED **azul** se enciende (humedad >= 80 %); a las 15:00 el **rojo** se enciende (temperatura >= 30 C).
3. Al completar 21:00, la secuencia vuelve a 00:00.

## 4. Activar la lectura REAL del DHT22
1. Cambia en `sketch.ino` la linea `const bool DIA_AUTOMATICO = true;` por `const bool DIA_AUTOMATICO = false;`.
2. Reinicia Wokwi (deten y vuelve a iniciar). Ahora el Arduino **lee** los valores del DHT22 conectado.
3. Haz clic en el sensor y modifica sus deslizadores. Prueba estos casos:
   - **25 C, 60 %**: los dos LED apagados.
   - **32 C, 60 %**: solo LED rojo encendido.
   - **25 C, 85 %**: solo LED azul encendido.
   - **32 C, 85 %**: los dos encendidos.
4. Si el DHT no esta bien conectado, aparecera `ERROR DHT22: comprueba 5V, GND y D2.`.

**Importante:** En modo automatico, Arduino simula datos en el codigo; NO cambia las barras del sensor DHT22. En modo sensor, el DHT22 entrega las lecturas elegidas manualmente en Wokwi. Ningun modo simula fisicamente el clima.

## 5. Guardar el trabajo en GitHub
1. Crea un **fork** del repositorio del profesor y clonalo con `git clone`.
2. Desde Wokwi, copia el `diagram.json` cableado y reemplaza ese archivo dentro del repositorio local clonado.
3. Ejecuta `git status`, `git diff diagram.json`, `git add diagram.json`, `git commit -m "Conecta circuito del taller"` y `git push`.
4. Comprueba en GitHub el nuevo commit y entrega el enlace a tu fork.

Si optaste por cambiar `DIA_AUTOMATICO` a `false`, copia ademas el `sketch.ino` modificado a tu carpeta local antes de hacer `git add`. La web de Wokwi no sincroniza por si sola con GitHub.
