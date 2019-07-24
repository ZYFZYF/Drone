-- if you wish to execute code contained in an external file instead,
-- use the require-directive, e.g.:
--
-- require 'myExternalFile'
--
-- Above will look for <V-REP executable path>/myExternalFile.lua or
-- <V-REP executable path>/lua/myExternalFile.lua
-- (the file can be opened in this editor with the popup menu over
-- the file name)

function sysCall_init()
    -- do some initialization here:

    -- Make sure you read the section on "Accessing general-type objects programmatically"
    -- For instance, if you wish to retrieve the handle of a scene object, use following instruction:
    --
    -- handle=sim.getObjectHandle('sceneObjectName')
    -- 
    -- Above instruction retrieves the handle of 'sceneObjectName' if this script's name has no '#' in it
    --
    -- If this script's name contains a '#' (e.g. 'someName#4'), then above instruction retrieves the handle of object 'sceneObjectName#4'
    -- This mechanism of handle retrieval is very convenient, since you don't need to adjust any code when a model is duplicated!
    -- So if the script's name (or rather the name of the object associated with this script) is:
    --
    -- 'someName', then the handle of 'sceneObjectName' is retrieved
    -- 'someName#0', then the handle of 'sceneObjectName#0' is retrieved
    -- 'someName#1', then the handle of 'sceneObjectName#1' is retrieved
    -- ...
    --
    -- If you always want to retrieve the same object's handle, no matter what, specify its full name, including a '#':
    --
    -- handle=sim.getObjectHandle('sceneObjectName#') always retrieves the handle of object 'sceneObjectName' 
    -- handle=sim.getObjectHandle('sceneObjectName#0') always retrieves the handle of object 'sceneObjectName#0' 
    -- handle=sim.getObjectHandle('sceneObjectName#1') always retrieves the handle of object 'sceneObjectName#1'
    -- ...
    --
    -- Refer also to sim.getCollisionhandle, sim.getDistanceHandle, sim.getIkGroupHandle, etc.
    base = sim.getObjectHandle('Quadricopter_base')
    target = sim.getObjectHandle('Quadricopter_target')
    rising_delay_rounds = 0
    rising_delay_rounds_limit = 50
    state = 'rising'
    approaching_close_rounds = 0
    landing_close_rounds = 0
end

function sysCall_actuation()
    -- put your actuation code here
    --
    -- For example:
    --
    -- local position=sim.getObjectPosition(handle,-1)
    -- position[1]=position[1]+0.001
    -- sim.setObjectPosition(handle,-1,position)
    qrcode_x = sim.getFloatSignal('QRcode_x')
    qrcode_y = sim.getFloatSignal('QRcode_y')
    qrcode_z = sim.getFloatSignal('QRcode_z')
    base_pos = sim.getObjectPosition(base, -1)
    target_pos = sim.getObjectPosition(target, -1)
        
    
    if state == 'rising' then 
        if qrcode_z ~= nil and qrcode_z > 0 then
            rising_delay_rounds = rising_delay_rounds + 1
        end
        target_pos[3] = target_pos[3] + 0.01 * (1.0 - rising_delay_rounds / rising_delay_rounds_limit)
        sim.setObjectPosition(target, -1, target_pos)
        if rising_delay_rounds >= rising_delay_rounds_limit then 
            state = 'approaching'
        end
    end
        
    if qrcode_z == nil or qrcode_z < 0 then 
        return
    end

    if state == 'approaching' then
        destination_pos = {qrcode_x, qrcode_y, target_pos[3]}
        standard_pos = target_pos
        error = {destination_pos[1] - standard_pos[1], destination_pos[2] - standard_pos[2], destination_pos[3] - standard_pos[3]}
        error_length = math.sqrt(error[1] * error[1] + error[2] * error[2] + error[3] * error[3])
        threshold = 0.02
        if error_length < threshold then 
            approaching_close_rounds = approaching_close_rounds + 1
            target_pos = destination_pos
        else
            target_pos = {target_pos[1] + error[1] / error_length * threshold,
                          target_pos[2] + error[2] / error_length * threshold,
                          target_pos[3]}
        end 
        sim.setObjectPosition(target, -1, target_pos)
        if approaching_close_rounds > 10 then 
            state = 'landing'
        end 
    end
    
    if state == 'landing' then
        destination_pos = {qrcode_x, qrcode_y, qrcode_z + 0.6}
        standard_pos = target_pos
        error = {destination_pos[1] - standard_pos[1], destination_pos[2] - standard_pos[2], destination_pos[3] - standard_pos[3]}
        error_length = math.sqrt(error[1] * error[1] + error[2] * error[2] + error[3] * error[3])
        threshold = 0.01
        if error_length < threshold then 
            landing_close_rounds = landing_close_rounds + 1
            target_pos = destination_pos
        else
            target_pos = {target_pos[1] + error[1] / error_length * threshold,
                          target_pos[2] + error[2] / error_length * threshold,
                          target_pos[3] + error[3] / error_length * threshold}
        end 
        sim.setObjectPosition(target, -1, target_pos)
        if landing_close_rounds > 10 then 
            sim.setFloatSignal('is_landing_finished', 1)
            sim.setFloatSignal('landing_begin_height', qrcode_z + 0.6)
            sim.setFloatSignal('landing_end_height', qrcode_z + 0.3)
        end 
    end
end

function sysCall_sensing()
    -- put your sensing code here
end

function sysCall_cleanup()
    -- do some clean-up here
end

-- You can define additional system calls here:
--[[
function sysCall_suspend()
end

function sysCall_resume()
end

function sysCall_dynCallback(inData)
end

function sysCall_jointCallback(inData)
    return outData
end

function sysCall_contactCallback(inData)
    return outData
end

function sysCall_beforeCopy(inData)
    for key,value in pairs(inData.objectHandles) do
        print("Object with handle "..key.." will be copied")
    end
end

function sysCall_afterCopy(inData)
    for key,value in pairs(inData.objectHandles) do
        print("Object with handle "..key.." was copied")
    end
end

function sysCall_beforeDelete(inData)
    for key,value in pairs(inData.objectHandles) do
        print("Object with handle "..key.." will be deleted")
    end
    -- inData.allObjects indicates if all objects in the scene will be deleted
end

function sysCall_afterDelete(inData)
    for key,value in pairs(inData.objectHandles) do
        print("Object with handle "..key.." was deleted")
    end
    -- inData.allObjects indicates if all objects in the scene were deleted
end

function sysCall_afterCreate(inData)
    for key,value in pairs(inData.objectHandles) do
        print("Object with handle "..value.." was created")
    end
end
--]]
