With Ada.Strings;
with Ada.Text_IO;
use Ada.Text_IO;
use Ada.Strings;
with Ada.Float_Text_IO;
with Ada.Integer_Text_IO;
use Ada.Integer_Text_IO;

procedure Main is
    N, Val, Tmp, Digit, Ord: Integer;
    Ord_Tmp, Digit_Tmp: Integer;
    Cnt: Integer;
    Prev_three: Integer;
    Infinity: Integer;
begin
    Ada.Integer_Text_IO.Get(Item => N);
    Infinity := 0;
    Digit_Tmp := N;
Inf_Loop:
    loop
        exit Inf_Loop when Digit_Tmp < 13;
        If Digit_Tmp mod 100 = 13 then
            Infinity := 1;
            Digit_Tmp := 0;
        end if;
        Digit_Tmp := Digit_Tmp / 10;
    end loop Inf_Loop;
    if Infinity = 1 then
        Ada.Text_IO.Put_Line("-1");
    else
        Cnt := 0;
For_Loop:
        For base in Integer range 4 .. N loop
            Tmp := N;
            Prev_three := 0;
        Digit_Loop:
            loop
                exit Digit_Loop when Tmp = 0;
                Digit := Tmp mod base;
                Ord_Tmp := Digit;
            Ord_Loop:
                loop
                    exit Ord_Loop when Ord_Tmp < 10;
                    Ord_Tmp := Ord_Tmp / 10;
                end loop Ord_Loop;
                if Digit mod 10 = 1 and Prev_three = 1 then
                    Cnt := Cnt + 1;
                    Prev_three := 0;
                    Tmp := 0;
                    Digit := 0;
                end if;
                If Ord_Tmp = 3 then
                    Prev_three := 1;
                else
                    Prev_three := 0;
                end if;
                Digit_Tmp := Digit;
                Thirteen_Loop:
                loop
                    exit Thirteen_loop when Digit_Tmp < 13;
                    if Digit_Tmp mod 100 = 13 then
                        Cnt := Cnt + 1;
                        Digit_Tmp := 0;
                        Tmp := 0;
                        Digit := 0;
                    end if;
                    Digit_Tmp := Digit_Tmp / 10;
                end loop Thirteen_Loop;
                Tmp := Tmp / base;
            end loop Digit_Loop;
        end loop For_Loop;
        Ada.Integer_Text_IO.Put(Item => Cnt, Width => 0);
    end if;
end Main;
