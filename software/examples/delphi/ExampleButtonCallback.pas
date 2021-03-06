program ExampleButtonCallback;

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
    procedure ButtonPressedCB(sender: TBrickletLCD16x2; const button: byte);
    procedure ButtonReleasedCB(sender: TBrickletLCD16x2; const button: byte);
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = 'XYZ'; { Change XYZ to the UID of your LCD 16x2 Bricklet }

var
  e: TExample;

{ Callback procedure for button pressed callback }
procedure TExample.ButtonPressedCB(sender: TBrickletLCD16x2; const button: byte);
begin
  WriteLn(Format('Button Pressed: %d', [button]));
end;

{ Callback procedure for button released callback }
procedure TExample.ButtonReleasedCB(sender: TBrickletLCD16x2; const button: byte);
begin
  WriteLn(Format('Button Released: %d', [button]));
end;

procedure TExample.Execute;
begin
  { Create IP connection }
  ipcon := TIPConnection.Create;

  { Create device object }
  lcd := TBrickletLCD16x2.Create(UID, ipcon);

  { Connect to brickd }
  ipcon.Connect(HOST, PORT);
  { Don't use device before ipcon is connected }

  { Register button pressed callback to procedure ButtonPressedCB }
  lcd.OnButtonPressed := {$ifdef FPC}@{$endif}ButtonPressedCB;

  { Register button released callback to procedure ButtonReleasedCB }
  lcd.OnButtonReleased := {$ifdef FPC}@{$endif}ButtonReleasedCB;

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
