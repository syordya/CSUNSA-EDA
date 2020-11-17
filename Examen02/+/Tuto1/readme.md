## Tutorial
### Programa: Entradas
Descargar el *dataset* [Dogs vs. Cats](https://www.kaggle.com/c/dogs-vs-cats/data) desde Kaggle.
Descomprimir la carpeta `train.zip` y nombrarla `dogs_vs_cats`.

### Programa: Requerimientos
Crearemos un entorno virtual donde instalaremos las librerías. Se asume, usted tiene instalado `python3`.
#### Entorno virtual
```
python -m venv venv
. venv/bin/activate
```
#### Instalando librerías
```
pip install -r requirements.txt
```

### Programa: Ejecución
```
python knn_classifier.py --dataset dogs_vs_cats
```
