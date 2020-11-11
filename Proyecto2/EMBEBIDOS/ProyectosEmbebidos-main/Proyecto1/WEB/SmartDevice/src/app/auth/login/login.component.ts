import { Component, OnInit } from '@angular/core';
import { FormGroup, FormControl } from '@angular/forms';
import { AuthService } from '../../../services/auth/auth.service';
import { Router } from '@angular/router';
import { User } from '../../../services/auth/user.interface';
@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent {
  loginForm = new FormGroup({
    email: new FormControl(''),
    password: new FormControl(''),
  });
  constructor(private authSvc: AuthService, private router: Router) {}

  async onGoogleLogin() {
    try {
      const user = await this.authSvc.loginGoogle();
      if (user) {
        this.checkUserIsVerified(user);
      }
    } catch (error) {
      console.log(error);
    }
  }

  async email() {
    const { email, password } = this.loginForm.value;
    try {
      const user = await this.authSvc.login(email, password);
      if (user) {
        this.router.navigate(['/pages/home']);
      }
    } catch (error) {
      console.log(error);
    }
  }

  async onLogin() {
    const { email, password } = this.loginForm.value;
    try {
      const user = await this.authSvc.login(email, password);
      if (user) {
        this.router.navigate(['/pages/home']);
      }
      else{
        const user = await this.authSvc.loginGoogle();
        if (user) {
          this.router.navigate(['/pages/home']);
        }
      }
    } catch (error) {
      console.log(error);
    }
  }

  private checkUserIsVerified(user: User) {
    if (user && user.emailVerified) {
      console.log("Entre")
      this.router.navigate(['/pages/home']);
    } else if (user) {
      console.log("Entre1")
      this.router.navigate(['/verification-email']);
    } else {
      console.log("Entre2")
      this.router.navigate(['/register']);
    }
  }
}
