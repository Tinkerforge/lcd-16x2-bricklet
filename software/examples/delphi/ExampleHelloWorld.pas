program ExampleHelloWorld;

{$ifdef MSWINDOWS}{$apptype CONSOLE}{$endif}
{$ifdef FPC}{$mode OBJFPC}{$H+}{$endif}

uses
  SysUtils, IPConnection, BrickletLCD16x2;

type
  TExample = class
  private
    ipcon: TIPConnection;
    lcd: TBrickletLCD16x2;
  public
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = '6ko'; { Change to your UID }

var
  e: TExample;

procedure TExample.Execute;
begin
  { Create IP connection }
  ipcon := TIPConnection.Create();

  { Create device object }
  lcd := TBrickletLCD16x2.Create(UID, ipcon);

  { Connect to brickd }
  ipcon.Connect(HOST, PORT);
  { Don't use device before ipcon is connected }

  { Turn backlight on }
  lcd.BacklightOn;

  { Write "Hello World" }
  lcd.WriteLine(0, 0, 'Hello World');

  WriteLn('Press key to exit');
  ReadLn;
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
