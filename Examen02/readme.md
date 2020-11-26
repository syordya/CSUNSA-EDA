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

## Preprocesamiento con la MEDIA
### Generar vector de características de imágenes del *dataset* con la media.
```
python feature_extractor_media.py --dataset moche_vs_yuan
```
<p align="center">
  <img width="70%" height="70%" src="img/a.PNG">
</p>

### Generar vector de características de una imagen de entrada con la media.

#### Con 3 vecinos
Una ceramica yuan:
<p align="center">
  <img width="10%" height="10%" src="img/1.png">
  <img width="40%" height="40%" src="img/1a.PNG">
</p>

<p align="center">
  <img width="40%" height="40%" src="img/1b.PNG">
</p>

```
python feature_extractor_one_media.py --image test2/1.png
```
<p align="center">
  <img width="70%" height="70%" src="img/b.PNG">
</p>

Una ceramica moche:
<p align="center">
  <img width="10%" height="10%" src="img/7.png">
  <img width="30%" height="30%" src="img/7a.PNG">
</p>
<p align="center">
  <img width="40%" height="40%" src="img/7b.PNG">
</p>

```
python feature_extractor_one_media.py --image test2/7.png
```
<p align="center">
  <img width="70%" height="70%" src="img/c.PNG">
</p>

#### Con 50 vecinos
Una ceramica moche:
<p align="center">
  <img width="70%" height="70%" src="img/e.PNG">
</p>

Una ceramica yuan:
<p align="center">
  <img width="70%" height="70%" src="img/d.PNG">
</p>

## Ejecución
```
node kdtree_media.js
```

salir deactivate
