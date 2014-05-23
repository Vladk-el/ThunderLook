
#include "includes/smtpClient/src/SmtpMime"

int smtp_test()
{
    // This is a first demo application of the SmtpClient for Qt project

    // First we need to create an SmtpClient object
    // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)

    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

    // We need to set the username (your email address) and the password
    // for smtp authentification.

    smtp.setUser("eliott.laversin@gmail.com");
    smtp.setPassword("chajotensim");

    // Now we create a MimeMessage object. This will be the email.

    MimeMessage message;

    message.setSender(new EmailAddress("eliott.laversin@gmail.com", "Eliott Laversin"));
    message.addRecipient(new EmailAddress("eliott.laversin@gmail.com", "Eliott Laversin"));
    message.setSubject("SmtpClient for Qt - Test in ThunderLook");

    // Now add some text to the email.
    // First we create a MimeText object.

    MimeText text;

    //text.setText("Hi,\nThis is a simple email message.\n");
    text.setText("Test\n");

    // Now add it to the mail

    message.addPart(&text);

    // Now we can send the mail

    /*smtp.connectToHost();
    smtp.login();
    smtp.sendMail(message);
    smtp.quit();*/
    return 0;
}

MimeMessage * construct()
{
    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

    smtp.setUser("eliott.laversin@gmail.com");
    smtp.setPassword("chajotensim");

    MimeMessage * message = new MimeMessage;

    message->setSender(new EmailAddress("eliott.laversin@gmail.com", "Eliott Laversin"));
    message->addRecipient(new EmailAddress("eliott.laversin@gmail.com", "Eliott Laversin"));
    message->setSubject("SmtpClient for Qt - Test in ThunderLook");

    MimeText text;

    text.setText("Test\n");

    message->addPart(&text);

    return message;
}
