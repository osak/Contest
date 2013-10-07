With Ada.Strings;
with Ada.Text_IO;
use Ada.Text_IO;
use Ada.Strings;
with Ada.Float_Text_IO;
with Ada.Integer_Text_IO;
use Ada.Integer_Text_IO;

procedure Main is
    type my_float is digits 5 range 0.0 .. 100.0;
    Str: String(1..100);
    Len: Natural;
    Num, Tmp: Integer;
    Prob: Float;
    Char: Character;
    P: Float;
begin
    Ada.Text_IO.Get_LIne(Item => Str, Last => Len);
    Ada.Float_Text_IO.Get(Item => P);
    Prob := 0.0;
For_Loop:
    for i in Integer range 1 .. Len loop
        if Str(i) = '1' then
            Prob := Prob + 1.0;
        end if;
        if Str(i) = '?' then
            Prob := Prob + P;
        end if;
    end loop For_Loop;
    Prob := Prob / FLoat(Len);
    Ada.Float_Text_IO.Put(Item => Prob, Fore => 1, Aft => 5, Exp => 0);
end Main;
