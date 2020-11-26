## Requerimientos
### Crear e inicializar entorno virtual de Python
```
python -m venv venv
.\venv\Scripts\activate
```

cd C:\Users\Kemely\Desktop\SEMESTRE2\EDA\Segundo_Examen\CSUNSA-EDA\Examen02\code
### Instalar librerías de Python y Node
```
pip install -r requirements.txt
npm install
```
```
cd src
```

## Preprocesamiento MEDIA
### Generar vector de características de imágenes del *dataset* con la media.
```
python feature_extractor_media.py --dataset moche_vs_yuan
```
### Generar vector de características de una imagen de entrada con la media.

Una ceramica moche:
```
python feature_extractor_one_media.py --image test2/1.png
```
Una ceramica yuan:
```
python feature_extractor_one_media.py --image test2/7.png
```

## Ejecución
```
node kdtree_media.js
```

salir deactivate
