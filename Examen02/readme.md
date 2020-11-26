## Requerimientos
### Ingresar donde va a estar nuestro codigo y Crear e inicializar entorno virtual de Python
```
Linux: python -m venv venv
Windows: .\venv\Scripts\activate
```

### Instalar librerías de Python y Node
```
pip install -r requirements.txt
npm install
```
```
cd src
```

## Preprocesamiento con la MEDIA (cv2.mean)
### Generar vector de características de imágenes del *dataset* con la media.
```
python feature_extractor_media.py --dataset moche_vs_yuan
```
<p align="center">
  <img width="70%" height="70%" src="img/a.PNG">
</p>
<p align="center">
  <img width="70%" height="70%" src="img/a1.PNG">
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

### Ejecución
```
node kdtree_media.js
```

## Preprocesamiento Media y Desviación Estándar (cv2.meanStdDev)

### Generar vector de características de imágenes del *dataset* .
```
python feature_extractor_STD.py --dataset moche_vs_yuan
```
<p align="center">
  <img width="70%" height="70%" src="img/a2.PNG">
</p>

### Generar vector de características de una imagen de entrada .
#### Con 3 vecinos
Una ceramica yuan:
```
python feature_extractor_one_STD.py --image test2/1.png
```
<p align="center">
  <img width="70%" height="70%" src="img/b1.PNG">
</p>

Una ceramica moche:
```
python feature_extractor_one_STD.py --image test2/7.png
```
<p align="center">
  <img width="70%" height="70%" src="img/c1.PNG">
</p>

### Ejecución
```
node kdtree_STD.js
```
### Contraste con solo la media:
Utilizamos una imagen en el medio de las tonalidades.
<p align="center">
  <img width="10%" height="10%" src="img/16.jpg">
</p>

Con 50 vecinos
#### cv2.mean
<p align="center">
  <img width="70%" height="70%" src="img/mean1.PNG">
</p>

#### cv2.meanStdDev
<p align="center">
  <img width="70%" height="70%" src="img/std1.PNG">
</p>

salir deactivate
