--** Codigo fuente del Proyect: Esky
-- **********************************
--
-- Archivo index.lua
-- *Lectura del archivo de configuracion de IP y guardado con autosalida a HOME


--Variables
local haySD = false
local existeArchivo = false
local vida = true
local ruta = "/3DSController.ini"

local c = 0

function main()
    Screen.refresh()
    Screen.clear(TOP_SCREEN)
	Screen.clear(BOTTOM_SCREEN)    
    Screen.flip()
end

main()


while true do
	pad = Controls.read()

	if Controls.check(pad,KEY_B) then
		System.exit()	
	end	
	
	if vida then
		--si no hay SD cortamos todo		  
		haySD = System.checkSDMC()
		if haySD ~= true then
			vida = false
		else
			--si hay SD comprobamos que exista el archivo. suponemos siempre que existe ya que la comprobacion de la SD de System.checkSDMC ha sido 
			--casi "instantanea". De todos modos, una comprobacion aqui de nuevo seria recomendable
			existeArchivo = System.doesFileExist(ruta)
			--Si no existe el archivo, lo creamos
			if existeArchivo ~= true then
			
			else
				if c == 0 then
					local file = io.open(ruta, FWRITE)
					local contenido = io.read(file, 0, io.size(file))
					local ip = string.sub(contenido, 84, 95)
					local puerto = string.sub(contenido, 104, 107)
					
					Screen.refresh()
					Screen.debugPrint(5,15, "IP: "..ip, Color.new(255,0,0), TOP_SCREEN)
					Screen.debugPrint(5, 30, "Puerto: "..puerto, Color.new(255,0,0), TOP_SCREEN)

					Screen.waitVblankStart()
					Screen.flip()
					io.close(file)
					
					c = 1
				end
			end			
		end			
	end	
end
