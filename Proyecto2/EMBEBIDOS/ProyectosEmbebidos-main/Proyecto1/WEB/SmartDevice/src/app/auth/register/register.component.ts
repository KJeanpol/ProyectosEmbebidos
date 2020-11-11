import { Component, OnInit } from '@angular/core';
import { FormGroup, FormControl } from '@angular/forms';
import { AuthService } from '../../../services/auth/auth.service';
import { Router } from '@angular/router';
import { User } from '../../../services/auth/user.interface';

@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.css']
})
export class RegisterComponent {
  registerForm = new FormGroup({
    email: new FormControl(''),
    password: new FormControl(''),
  });

  constructor(private authSvc: AuthService, private router: Router) {}

  async onRegister() {
    const { email, password } = this.registerForm.value;
    try {
      const user = await this.authSvc.register(email, password);
      if (user) {
        this.checkUserIsVerified(user);
      }
    } catch (error) {
      console.log(error);
    }
  }

  private checkUserIsVerified(user: User) {
    if (user && user.emailVerified) {
      this.router.navigate(['/home']);
    } else if (user) {
      this.router.navigate(['/verification-email']);
    } else {
      this.router.navigate(['/register']);
    }
  }
}