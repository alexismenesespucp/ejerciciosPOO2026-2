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
/*CREATE TABLE Mapa (
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

CREATE TABLE MapaCelda(
	IdMapaCelda INT IDENTITY(1,1) PRIMARY KEY,
	IdMapa INT NOT NULL,
	Fila INT NOT NULL,
	Columna INT NOT NULL,
	EsMuro BIT NOT NULL,
	CONSTRAINT FK_Celda_Mapa FOREIGN KEY(IdMapa) REFERENCES Mapa(IdMapa) ON DELETE CASCADE
); */


/*CREATE PROCEDURE usp_InsertarMapa
	@TotalFilas INT,
	@TotalColumnas INT,
	@InicioFila INT,
	@InicioColumna INT,
	@FinFila INT,
	@FinColumna INT,
    @TipoDistancia VARCHAR(20), 
	@MovimientoCeldaHorizontal INT,
	@MovimientoCeldaVertical INT,
	@MovimientoCeldaDiagonal INT,
	@IdMapaGenerado INT OUTPUT
AS BEGIN
	set NOCOUNT ON;
	INSERT INTO Mapa(TotalFilas,TotalColumnas,InicioFila,InicioColumna,
					 FinFila,FinColumna,TipoDistancia,MovimientoCeldaHorizontal,
					 MovimientoCeldaVertical,MovimientoCeldaDiagonal)
				VALUES (@TotalFilas,@TotalColumnas,@InicioFila,@InicioColumna,
					 @FinFila,@FinColumna,@TipoDistancia,@MovimientoCeldaHorizontal,
					 @MovimientoCeldaVertical,@MovimientoCeldaDiagonal);
	SET @IdMapaGenerado = SCOPE_IDENTITY();
END;*/


CREATE PROCEDURE usp_InsertarCeldaMapa
	@IdMapa INT,
	@Fila INT,
	@Columna INT,
	@EsMuro BIT
AS BEGIN
   SET NOCOUNT ON;
   INSERT INTO MapaCelda(IdMapa,Fila,Columna,EsMuro)
   VALUES (@IdMapa,@Fila,@Columna,@EsMuro);
END;