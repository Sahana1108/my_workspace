document.addEventListener("DOMContentLoaded", function() {     // this addEventListener is an exisitng js function uses  
                                                                // the DOMContentLoaded event to access the input from 
                                                                // the html form once the form has been filled out

    var password = document.getElementById("password");  // password and confirmpassword are the two fields that will
    var confirmpassword = document.getElementById("confirmpassword");                                 // be compared

    function validatePassword() {
        if (password.value != confirmpassword.value) {  // checking is they are both the same
            confirmpassword.setCustomValidity("Passwords must match"); // if they are different, then this error message will be
                                                                       // displayed to the user
        } else {
            confirmpassword.setCustomValidity("");
        }
    }

    password.addEventListener("input", validatePassword);     // specifies that the user inputs must be checked using the validatePassword function
    confirmpassword.addEventListener("input", validatePassword); 
});
