CREATE TABLE mapa (
	IdMapa INT Identity(1,1) primary KEY,
	FechaCreacion DATETIME DEFAULT GETDATE(),
	TotalFilas INT NOT NULL,
	TotalColumnas INT NOT NULL,
	InicioFila INT NOT NULL,
	InicioColumna INT NOT NULL,
	FinFila INT NOT NULL,
	FinColumna INT NOT NULL,
    TipoDistancia VARCHAR(20) default 'manhathan',
	MovimientoCeldaHorizontal INT NOT NULL,
	MovimientoCeldaVertical INT NOT NULL,
	MovimientoCeldaDiagonal INT NOT NULL,
);

/* Quiero una vista para visual studio c++ cli que nos permita utilizar información 
de mapas anteriores. (Podamos actualizar, modificar, eliminar)
También debería de haber un botón para poder volver a correr el algorimo A*.
Tener un boton para generar el mapa.
Un boton para actualizar los pesos (Que es diferente al boton generar, 
el boton generar, genera un nuevo mapa)
También deberiamos de poder generar nuevos mapas con diferente caracteristicas.
Y deberíamos de visualizar las caracteristicas actuales del mapa que estamos visualizando.

También deberiamos de ver la solución de A* paso por paso, con la lista y 
los pesos de la solución.
*/