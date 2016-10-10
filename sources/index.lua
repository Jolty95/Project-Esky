--** Código fuente del Proyect: Esky
-- **********************************
--
-- Archivo index.lua
-- *Lectura del archivo de configuración de IP y guardado con autosalida a HOME


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
					local oldIP = io.read(file, 83, io.size(file))
					io.close(file)
					local test = io.open("/test.txt",FCREATE) 
					io.write(test, 0, oldIP, 100)
					io.close(test)
					Screen.refresh()
					Screen.debugPrint(5,15, "IP: "..oldIP, Color.new(255,0,0), TOP_SCREEN)
					Screen.waitVblankStart()
					c = 1
				end
			end			
		end			
	end	
end
