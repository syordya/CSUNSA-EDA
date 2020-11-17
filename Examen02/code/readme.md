## Requerimientos
### Crear e inicializar entorno virtual de Python
```
python -m venv venv
. venv/bin/activate
```
### Instalar librerías de Python y Node
```
pip install -r requirements.txt
npm install
```

## Preprocesamiento
### Generar vector de características de imágenes del *dataset*.
```
python feature_extractor.py --dataset ../../data/dogs_vs_cats
```
### Generar vector de características de imágenes de entrada.
```
python feature_extractor_one.py --image ../../data/tests/74.jpg
```

## Ejecución
```
node kdtree.js
```
