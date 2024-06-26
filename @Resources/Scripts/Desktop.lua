function Initialize()
end

function Update()
end

function GetDesktopCount()
    local linkedMeasure = SELF:GetOption('LinkToDesktopIDS', '')
    local DesktopMeasure = SKIN:GetMeasure(linkedMeasure)
    local BinaryIDs = DesktopMeasure:GetStringValue()
    local DesktopCount = 0
    
    for ID in string.gmatch(BinaryIDs, "(%S+)") do
        DesktopCount = DesktopCount + 1
    end
    
    return DesktopCount
end

function GetCurrentDesktop()
    local linkedMeasure = SELF:GetOption('LinkToDesktopIDS', '')
    local DesktopMeasure = SKIN:GetMeasure(linkedMeasure)
    local BinaryIDs = DesktopMeasure:GetStringValue()
    local DesktopCount = 0

    local linkedMeasure2 = SELF:GetOption('LinkToCurrentDesktop', '')
    local DesktopMeasure2 = SKIN:GetMeasure(linkedMeasure2)
    local BinaryID = DesktopMeasure2:GetStringValue()

    for ID in string.gmatch(BinaryIDs, "(%S+)") do
        DesktopCount = DesktopCount + 1
        if (BinaryID == ID) then
            return DesktopCount
        end
    end
end
