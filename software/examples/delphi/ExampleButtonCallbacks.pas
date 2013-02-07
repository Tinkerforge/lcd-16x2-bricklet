program ExampleButtonCallbacks;

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
    procedure PressedCB(sender: TBrickletLCD16x2; const i: byte);
    procedure ReleasedCB(sender: TBrickletLCD16x2; const i: byte);
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = '6ko'; { Change to your UID }

var
  e: TExample;

{ Callback functions for button status }
procedure TExample.PressedCB(sender: TBrickletLCD16x2; const i: byte);
begin
  WriteLn(Format('Pressed: %d', [i]));
end;

procedure TExample.ReleasedCB(sender: TBrickletLCD16x2; const i: byte);
begin
  WriteLn(Format('Released: %d', [i]));
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

  { Register button status callbacks to procedure PressedCB and ReleasedCB }
  lcd.OnButtonPressed := {$ifdef FPC}@{$endif}PressedCB;
  lcd.OnButtonReleased := {$ifdef FPC}@{$endif}ReleasedCB;

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
