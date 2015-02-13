Imports Tinkerforge

Module ExampleUnicode
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "6ko" ' Change to your UID

    ' Maps a normal UTF-16 encoded string to the LCD charset
    Function UTF16ToKS0066U(ByVal utf16 As String) As String
        Dim ks0066u As String = ""
        Dim c As Char
        Dim i As Integer = 0

        While i < utf16.Length
            Dim codePoint As Integer = Char.ConvertToUtf32(utf16, i)

            if Char.IsSurrogate(utf16, i) Then
                ' Skip low surrogate
                i += 1
            End If

            ' ASCII subset from JIS X 0201
            if (codePoint >= &H0020) And (codePoint <= &H007e) Then
                ' The LCD charset doesn't include '\' and '~', use similar characters instead
                Select Case codePoint
                    Case &H005c
                        c = Chr(&H00a4) ' REVERSE SOLIDUS maps to IDEOGRAPHIC COMMA
                    Case &H007e
                        c = Chr(&H002d) ' TILDE maps to HYPHEN-MINUS
                    Case Else
                        c = Chr(codePoint)
                End Select
            ' Katakana subset from JIS X 0201
            Else If (codePoint >= &Hff61) And (codePoint <= &Hff9f) Then
                c = Chr(codePoint - &Hfec0)
            ' Special characters
            Else
                Select Case codePoint
                    Case &H00a5
                        c = Chr(&H5c) ' YEN SIGN
                    Case &H2192
                        c = Chr(&H7e) ' RIGHTWARDS ARROW
                    Case &H2190
                        c = Chr(&H7f) ' LEFTWARDS ARROW
                    Case &H00b0
                        c = Chr(&Hdf) ' DEGREE SIGN maps to KATAKANA SEMI-VOICED SOUND MARK
                    Case &H03b1
                        c = Chr(&He0) ' GREEK SMALL LETTER ALPHA
                    Case &H00c4
                        c = Chr(&He1) ' LATIN CAPITAL LETTER A WITH DIAERESIS
                    Case &H00e4
                        c = Chr(&He1) ' LATIN SMALL LETTER A WITH DIAERESIS
                    Case &H00df
                        c = Chr(&He2) ' LATIN SMALL LETTER SHARP S
                    Case &H03b5
                        c = Chr(&He3) ' GREEK SMALL LETTER EPSILON
                    Case &H00b5
                        c = Chr(&He4) ' MICRO SIGN
                    Case &H03bc
                        c = Chr(&He4) ' GREEK SMALL LETTER MU
                    Case &H03c2
                        c = Chr(&He5) ' GREEK SMALL LETTER FINAL SIGMA
                    Case &H03c1
                        c = Chr(&He6) ' GREEK SMALL LETTER RHO
                    Case &H221a
                        c = Chr(&He8) ' SQUARE ROOT
                    Case &H00b9
                        c = Chr(&He9) ' SUPERSCRIPT ONE maps to SUPERSCRIPT (minus) ONE
                    Case &H00a4
                        c = Chr(&Heb) ' CURRENCY SIGN
                    Case &H00a2
                        c = Chr(&Hec) ' CENT SIGN
                    Case &H2c60
                        c = Chr(&Hed) ' LATIN CAPITAL LETTER L WITH DOUBLE BAR
                    Case &H00f1
                        c = Chr(&Hee) ' LATIN SMALL LETTER N WITH TILDE
                    Case &H00d6
                        c = Chr(&Hef) ' LATIN CAPITAL LETTER O WITH DIAERESIS
                    Case &H00f6
                        c = Chr(&Hef) ' LATIN SMALL LETTER O WITH DIAERESIS
                    Case &H03f4
                        c = Chr(&Hf2) ' GREEK CAPITAL THETA SYMBOL
                    Case &H221e
                        c = Chr(&Hf3) ' INFINITY
                    Case &H03a9
                        c = Chr(&Hf4) ' GREEK CAPITAL LETTER OMEGA
                    Case &H00dc
                        c = Chr(&Hf5) ' LATIN CAPITAL LETTER U WITH DIAERESIS
                    Case &H00fc
                        c = Chr(&Hf5) ' LATIN SMALL LETTER U WITH DIAERESIS
                    Case &H03a3
                        c = Chr(&Hf6) ' GREEK CAPITAL LETTER SIGMA
                    Case &H03c0
                        c = Chr(&Hf7) ' GREEK SMALL LETTER PI
                    Case &H0304
                        c = Chr(&Hf8) ' COMBINING MACRON
                    Case &H00f7
                        c = Chr(&Hfd) ' DIVISION SIGN
                    Case &H25a0
                        c = Chr(&Hff) ' BLACK SQUARE
                    Case Else
                        c = Chr(&Hff) ' BLACK SQUARE
                End Select
            End If

            ' Special handling for 'x' followed by COMBINING MACRON
            If c = Chr(&Hf8) Then
                If Not ks0066u.EndsWith("x") Then
                    c = Chr(&Hff) ' BLACK SQUARE
                End If

                If ks0066u.Length > 0 Then
                    ks0066u = ks0066u.Remove(ks0066u.Length - 1, 1)
                End If
            End If

            ks0066u += c
            i += 1
        End While

        Return ks0066u
    End Function

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim lcd As New BrickletLCD16x2(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Turn backlight on
        lcd.BacklightOn()

        ' Write a string using the UTF16ToKS0066U function to map to the LCD charset
        lcd.WriteLine(0, 0, UTF16ToKS0066U("Stromstärke: 5µA"))

        ' Write a string directly including characters from the LCD charset
        lcd.WriteLine(1, 0, "Drehzahl: 1000s" + Chr(&He9))

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
