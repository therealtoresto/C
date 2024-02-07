# TESTS

:) credit.c exists.
:) credit.c compiles.
:( identifies 378282246310005 as AMEX
    expected "AMEX\n", not "INVALID\n"
:( identifies 371449635398431 as AMEX
    expected "AMEX\n", not "INVALID\n"
:( identifies 5555555555554444 as MASTERCARD
    expected "MASTERCARD\n", not "INVALID\n"
:( identifies 5105105105105100 as MASTERCARD
    expected "MASTERCARD\n", not "INVALID\n"
:( identifies 4111111111111111 as VISA
    expected "VISA\n", not "INVALID\n"
:( identifies 4012888888881881 as VISA
    expected "VISA\n", not "INVALID\n"
:) identifies 1234567890 as INVALID
:) identifies 369421438430814 as INVALID
:) identifies 4062901840 as INVALID
:) identifies 5673598276138003 as INVALID
:) identifies 4111111111111113 as INVALID
:) rejects a non-numeric input of "foo"
:) rejects a non-numeric input of ""
