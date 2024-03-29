/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:54:10 by wael-mos          #+#    #+#             */
/*   Updated: 2019/11/05 15:06:04 by evogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include <float.h>

typedef struct	s_vec
{
	float		x;
	float		y;
	float		z;
}				t_vec;

typedef struct	s_vec4
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4;

typedef struct	s_matrix
{
	t_vec4		row0;
	t_vec4		row1;
	t_vec4		row2;
	t_vec4		row3;
}				t_matrix;

typedef struct	s_ray
{
	t_vec		ori;
	t_vec		dir;
}				t_ray;

typedef struct	s_col
{
	float		r;
	float		g;
	float		b;
}				t_col;

typedef struct	s_cam
{
	t_vec		pos;
	t_vec		rot;
	float		fov;
}				t_cam;

typedef struct	s_light
{
	t_vec		pos;
	t_col		col;
}				t_light;

/*
** The objects : 0=plane, 1=sphere, 2=cylinder, 3=cone
*/
typedef struct	s_obj
{
	uint8_t		type;
	t_vec		pos;
	float		rad;
	t_vec		rot;
	t_col		col;
	t_ray		hit;
}				t_obj;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*data;

}				t_mlx;

typedef struct	s_env
{
	int			win_x;
	int			win_y;
	t_mlx		mlx;
	t_cam		cam;
	int			num_light;
	t_light		*lights;
	int			num_obj;
	t_obj		*objs;
	float		ambient;
}				t_env;

float			deg2rad(int d);
t_vec			vec(float x, float y, float z);
t_vec4			vec4(float x, float y, float z, float w);
t_col			color(float red, float green, float blue);
void			add_color(t_col *ori, t_col *add, float amount);
t_vec			sub_vec(t_vec v1, t_vec v2);
float			dot(t_vec v1, t_vec v2);
t_vec			cross(t_vec v1, t_vec v2);
t_vec			scale(float c, t_vec v);
t_vec			add_vec(t_vec v1, t_vec v2);
float			magnitude(t_vec v);
t_vec			normalize(t_vec v);

t_vec			rotate_x(t_vec pt, double theta);
t_vec			rotate_y(t_vec pt, double theta);
t_vec			rotate_z(t_vec pt, double theta);
t_vec			rotate_full(t_vec ori, t_vec rot);

int				parsing(char **av, t_env *env);
void			check_error(char *line, size_t num_hash);
int				read_objects(char *line, t_env *env, int num_line);
t_vec			get_axe(t_vec rot);

int				render(t_env *env);
int				cast_ray(t_env *env, t_ray *ray);
t_obj			*get_obj_intersect(t_env *env, t_ray *ray);
int				sphere_intersect(t_ray *r, t_obj *s, float *t);
int				cylinder_intersect(t_ray *r, t_obj *s, float *t);
int				plane_intersect(t_ray *r, t_obj *s, float *t);
int				cone_intersect(t_ray *r, t_obj *s, float *t);
t_vec			get_phit_normal(t_vec p_hit, t_obj *obj);

int				deal_key(int key, void *s);
int				deal_close(void);
int				deal_expose(t_env *env);
int				error_mlx(void);
void			errormsg(int msg);
void			freetab(char **tab);

#endif
