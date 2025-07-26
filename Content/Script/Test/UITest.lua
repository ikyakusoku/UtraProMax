local M = UnLua.Class()

function M:ReceiveConstruct()
    self.Text1:SetText("LuaConstruct")
end

function M:Construct()
    self.Text1:SetText("LuaConstruct2")
end

return M